import React from 'react';
import ReactDOM from 'react-dom';
import MyComponent1 from './MyComponent1';
import MyComponent2 from './MyComponent2';

ReactDOM.render(
  <>
    <MyComponent1/>
    <hr />
    <MyComponent2 />
  </>,
  document.getElementById('app')
);