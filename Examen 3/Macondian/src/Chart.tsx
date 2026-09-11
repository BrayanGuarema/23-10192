///
/// Chart
///

interface Props {
  data: number[];
};

const Chart = ({ data }: Props) => {
  const values = data.length > 0 ? data : [0, 1, 2, 3, 4, 5];
  const width = 640;
  const height = 320;
  const padding = 28;
  const maxValue = Math.max(...values, 1);
  const minValue = Math.min(...values, 0);
  const range = Math.max(maxValue - minValue, 1);

  const points = values.map((value, index) => {
    const x = padding + (index / Math.max(values.length - 1, 1)) * (width - padding * 2);
    const y = height - padding - ((value - minValue) / range) * (height - padding * 2);
    return `${x},${y}`;
  }).join(' ');

  return (
    <div className="chart-panel">
      <h3>Procesamiento del sistema</h3>
      <svg viewBox={`0 0 ${width} ${height}`} className="chart-svg" role="img" aria-label="Macondian data series chart">
        <line x1={padding} y1={height - padding} x2={width - padding} y2={height - padding} className="chart-axis" />
        <line x1={padding} y1={padding} x2={padding} y2={height - padding} className="chart-axis" />
        <polyline points={points} className="chart-line" />
      </svg>
    </div>
  );
};

export default Chart;
