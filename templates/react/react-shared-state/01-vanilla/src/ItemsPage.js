import React from 'react';
import ItemSummary from './ItemSummary';
import ItemList from './ItemList';
import ItemAdder from './ItemAdder';

export default ({items, addItem}) => (
  <div>
    <ItemSummary items={items} />
    <hr />
    <ItemList items={items} />
    <hr />
    <ItemAdder addItem={addItem} />
  </div>
);
