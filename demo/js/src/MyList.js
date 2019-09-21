import React from 'react';
import fetch from 'isomorphic-fetch';

async function request() {
  const response = await fetch('http://localhost:5000/api/getSuccessResponse');
  const json = await response.json();
  return json;
}

// function request()
// {
//   fetch('http://localhost:5000/api/getSuccessResponse')
//   .then(
//     function(response) {
//       if (response.status !== 200) {
//         console.log('Looks like there was a problem. Status Code: ' + response.status);
//         return;
//       }
//         response.json().then(function(data) {
//             console.log(data);
//             return  data;
//         });
//     }
//   )
//   .catch(function(err) {
//     console.log('Fetch Error :-S', err);
//   });
//     console.log("I am request");
// }

class MyList extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      component: null,
    };
  }

  async componentDidMount() {
    console.log('componentDidMount');
    const myListResponse = await request();
    this.setState({ component: myListResponse });
  }

  // shouldComponentUpdate()
  // {
  //     console.log('shouldComponentUpdate');
  //     const {component} = this.state;
  //     if (component==null)
  //     {
  //        console.log('i shouldnet render yet');
  //        return false;
  //     }
  //     return true;
  // }
  render() {
    console.log('render');
    const { component } = this.state;
    if (component == null) {
      return <div>not yet...</div>;
    }
    return <div>{component}</div>;
  }
}

export default MyList;
