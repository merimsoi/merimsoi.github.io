import React from 'react';
import fetch from 'isomorphic-fetch';

async function request() {
  const response = await fetch('http://localhost:5000/api/getSuccessResponse');
  const json = await response.json();
  return json;
}

class MyStateList extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      artists: null,
    };
  }

  async componentDidMount() {
    console.log('MyStateList componentDidMount');
    const myListResponse = await request();
    this.setState({ artists: myListResponse });
  }

  render() {
    const { artists } = this.state;
    if (artists == null) {
      return <div>Loading of MyStateList...</div>;
    }
    return (
      <div>
        <h1>MTV Base Headline Artists 2019</h1>
        <div> My sourse is state list fetch </div>
        <div>
          {artists.map(artist => (
            <div id="card-body" key={artist.id}>
              <div className="card">
                <h2>{artist.name}</h2>
                <p>genre:{artist.genre}</p>
                <p>Album released:{artist.albums}</p>
              </div>
            </div>
          ))}
        </div>
      </div>
    );
  }
}

export default MyStateList;
