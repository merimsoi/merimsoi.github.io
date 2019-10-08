import React from 'react';
import fetch from 'isomorphic-fetch';

async function request() {
  const response = await fetch('http://localhost:5000/api/getFailedResponse');
  return response;
}

class MyFailList extends React.Component {
  constructor(props) {
    super(props);
    this.state = { component: null };
  }

  async componentDidMount() {
    const result = await request();
    this.setState({ component: result });
  }

  render() {
    const { component } = this.state;
    if (component !== null) {
      return <div>{component}</div>;
    }
    return <></>;
  }
}

export default MyFailList;
