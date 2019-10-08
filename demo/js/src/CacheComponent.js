import React from 'react';

import { withCache } from './cache/withCache';
import { cacheFetche } from './cache/cacheProvider';

const CacheComponent = withCache(props => {
  const artists = cacheFetche(props.cache);
  return (
    <div>
      <h1>MTV Base Headline Artists 2019</h1>
      <div> My sourse is cached fetch </div>
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
});

export default CacheComponent;
