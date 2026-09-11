///
/// Image
///

interface Props {
  image: string; 
};

const Image = ({ image }: Props) => {
  const src = new URL(`../images/${image}`, import.meta.url).href;
  return (
    <div className="image-frame">
      <img className="image-content" src={src} alt={image} />
    </div>
  );
};

export default Image;
