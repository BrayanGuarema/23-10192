export type SensorReading = {
  batch: number;
  sensorId: string;
  model: 'Y' | 'L';
  microarray: number[];
};

const median = (values: number[]) => {
  if (values.length === 0) return 0;
  const sorted = [...values].sort((a, b) => a - b);
  const middle = Math.floor(sorted.length / 2);
  if (sorted.length % 2 === 0) {
    return (sorted[middle - 1] + sorted[middle]) / 2;
  }
  return sorted[middle];
};

const normalize = (value: number) => Number(value.toFixed(4));

export const parseSensorMessage = (raw: string): SensorReading | null => {
  const trimmed = raw.trim();
  if (!trimmed || trimmed.startsWith('Batch')) return null;

  const match = trimmed.match(/^(\d+)\s+([A-Z]+\d+)\s+\[\s*(.*)\s*\]$/i);
  if (!match) return null;

  const [, rawIndex, sensorId, data] = match;
  const microarray = data
    .split(/\s+/)
    .filter(Boolean)
    .map(Number)
    .filter((value) => Number.isFinite(value));

  if (microarray.length === 0) return null;

  const model = sensorId.startsWith('Y') ? 'Y' : 'L';
  return {
    batch: Number(rawIndex),
    sensorId: sensorId.toUpperCase(),
    model,
    microarray,
  };
};

export const computeMacondoForSensor = (
  sensor: SensorReading,
  toleranceRatio = 0.08,
): number => {
  const representative = median(sensor.microarray);
  const radius = Math.max(toleranceRatio * Math.abs(representative), 1e-6);
  const filtered = sensor.microarray.filter(
    (value) => Math.abs(value - representative) <= radius,
  );

  const chosen = filtered.length > 0 ? filtered : sensor.microarray;
  const value = chosen.reduce((sum, item) => sum + item, 0) / chosen.length;
  return normalize(value);
};

export const aggregateBatch = (
  sensors: SensorReading[],
  toleranceRatio = 0.08,
): number => {
  if (sensors.length === 0) return 0;

  const sensorValues = sensors.map((sensor) => computeMacondoForSensor(sensor, toleranceRatio));
  const representative = median(sensorValues);
  const radius = Math.max(toleranceRatio * Math.abs(representative), 1e-6);
  const filtered = sensorValues.filter((value) => Math.abs(value - representative) <= radius);
  const chosen = filtered.length > 0 ? filtered : sensorValues;
  const batchValue = chosen.reduce((sum, item) => sum + item, 0) / chosen.length;
  return normalize(batchValue);
};
