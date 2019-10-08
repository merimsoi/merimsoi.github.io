import React from 'react';

class ReduxList extends React.Component {
  componentDidMount() {
    console.log('component did mount in redux list called');
    const { onFetchList } = this.props;
    onFetchList();
  }

  render() {
    const { list } = this.props;
    if (list == null) {
      return <div>Loading of ReduxList...</div>;
    }
    return (
      <div>
        <h1>MTV Base Headline Artists 2019</h1>
        <div> My sourse is redux component </div>
        <div>
          {list.map(artist => (
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

export default ReduxList;
