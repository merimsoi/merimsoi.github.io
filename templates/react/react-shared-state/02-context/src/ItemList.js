import React from 'react';
import ItemRow from './ItemRow';
import ItemsContext from './ItemsContext';

export default () => (
  <ItemsContext.Consumer>
    {value => (
      <div>
        <h2>The List of Items</h2>
        <ul>
          {value.items.map(item => <ItemRow key={item.id} item={item} />)}
        </ul>
      </div>
    )}
  </ItemsContext.Consumer>
);
