import React from 'react';

const FancyButton = React.forwardRef((props, ref) => (
  <button type="button" ref={ref} className="FancyButton">
    {props.children}
  </button>
));

export default FancyButton;
