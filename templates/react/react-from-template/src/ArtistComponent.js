import React from 'react';
import './App.css';
import artists from './store';

class ArtistComponent extends React.Component {
  constructor(props) {
    super(props);
    this.sleep = this.sleep.bind(this);

    this.state = {
      artistsList: [],
    };
  }

  async componentDidMount() {
    console.log('Taking a break...');
    console.log(this.state.artistsList);
    await this.sleep(5000);
    console.log('after break');
    console.log(this.state.artistsList);
    this.setState({ artistsList: artists });
  }

  // eslint-disable-next-line class-methods-use-this
  sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
  }

  render() {
    return (
      <div>
        {this.state.artistsList.map(artist => (
          <div id="card-body" key={artist.id}>
            <div className="card">
              <h2>{artist.name}</h2>
              <p>
                genre:
                {' '}
                {artist.genre}
              </p>
              <p>
                Albums released:
                {' '}
                {artist.albums}
              </p>
            </div>
          </div>
        ))}
      </div>
    );
  }
}

export default ArtistComponent;
