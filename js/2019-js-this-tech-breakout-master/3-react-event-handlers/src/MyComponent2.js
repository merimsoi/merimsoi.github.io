import React from 'react';

/*
1. CLI: npm install --save-dev @babel/plugin-proposal-class-properties
2. .babelrc: { "plugins": ["@babel/plugin-proposal-class-properties"], }
*/

class MyComponent2 extends React.Component {
  state = {
    name: '',
  }

  handleButtonClick_Fred = () => {
    this.setState({ name: 'Fred' });
  }

  render() {
    return <>
      <p>My name is: <u>{ this.state.name }</u></p>
      <p><button type="button" onClick={this.handleButtonClick_Fred}>Fred</button></p>
    </>
  }
}

export default MyComponent2;