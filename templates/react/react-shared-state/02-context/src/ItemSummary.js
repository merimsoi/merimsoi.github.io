import React from 'react';
import ItemsContext from './ItemsContext';

export default () => (
  <ItemsContext.Consumer>
    {value => (
      <div>
        <h2>Item Summary</h2>
        <p>There are: {value.items.length} items in the list!</p>
      </div>
    )}
  </ItemsContext.Consumer>
);
