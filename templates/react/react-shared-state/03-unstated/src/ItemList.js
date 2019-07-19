import React from 'react';
import { Subscribe } from 'unstated';
import ItemRow from './ItemRow';
import ItemsContainer from './ItemsContainer';

export default () => (
  <Subscribe to={[ItemsContainer]}>
    {container => (
      <div>
        <h2>The List of Items</h2>
        <ul>
          {container.state.items.map(item => <ItemRow key={item.id} item={item} />)}
        </ul>
      </div>
    )}
  </Subscribe>
);
