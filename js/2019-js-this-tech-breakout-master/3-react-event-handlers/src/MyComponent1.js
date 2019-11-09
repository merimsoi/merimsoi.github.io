import React from 'react';

class MyComponent1 extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      name: '',
    }

    this.handleButtonClick_Charlie = this.handleButtonClick_Charlie.bind(this);

    this.handleButtonClick_Elaine = () => {
      this.setState({ name: 'Elaine' });
    }
  }

  handleButtonClick_Alice() {
    this.setState({ name: 'Alice' });
  }

  handleButtonClick_Bob() {
    this.setState({ name: 'Bob' });
  }

  handleButtonClick_Charlie() {
    this.setState({ name: 'Charlie' });
  }

  render() {
    return <>
      <p>My name is: <u>{ this.state.name }</u></p>
      <p><button type="button" onClick={this.handleButtonClick_Alice}>Alice</button> passes a class function to react (react will call the class function when button is clicked)</p>
      <p><button type="button" onClick={() => { this.handleButtonClick_Bob() }}>Bob</button> passes an inline arrow function to react (react will call the arrow function when button is clicked)</p>
      <p><button type="button" onClick={this.handleButtonClick_Charlie}>Charlie</button> passes a class "bound" function to react (react will call the bound class function when button is clicked)</p>
      <p><button type="button" onClick={() => { this.setState({ name: 'Diana' }); }}>Diana</button> passes an inline arrow function to react (react will call the arrow function when button is clicked)</p>
      <p><button type="button" onClick={this.handleButtonClick_Elaine}>Elaine</button> passes a class arrow function to react (react will call the class arrow function when button is clicked)</p>
    </>
  }
}

export default MyComponent1;