import React from 'react';
import ItemSummary from './ItemSummary';
import ItemList from './ItemList';
import ItemAdder from './ItemAdder';

export default () => (
  <div>
    <ItemSummary />
    <hr />
    <ItemList />
    <hr />
    <ItemAdder />
  </div>
);
