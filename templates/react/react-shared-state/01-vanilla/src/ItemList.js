import React from 'react';
import ItemRow from './ItemRow';

export default ({items}) => (
  <div>
    <h2>The List of Items</h2>
    <ul>
      {items.map(item => <ItemRow key={item.id} item={item} />)}
    </ul>
  </div>
);
