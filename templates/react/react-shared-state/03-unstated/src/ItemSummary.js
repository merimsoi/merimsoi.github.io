import React from 'react';
import { Subscribe } from 'unstated';
import ItemsContainer from './ItemsContainer';

export default () => (
  <Subscribe to={[ItemsContainer]}>
    {container => (
      <div>
        <h2>Item Summary</h2>
        <p>There are: {container.state.items.length} items in the list!</p>
      </div>
    )}
  </Subscribe>
);
