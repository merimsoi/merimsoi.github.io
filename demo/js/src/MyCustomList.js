import React from 'react';

import { withCache } from './cache/withCache';
import { cacheFetche } from './cache/cacheProvider';

const MyCustomList = withCache(props => {
  const result = cacheFetche(props.cache);
  return <div>{result}</div>;
});

export default MyCustomList;
