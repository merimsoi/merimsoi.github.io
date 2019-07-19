import React from 'react';
import { Subscribe } from 'unstated';
import ItemSummary from './ItemSummary';
import ItemList from './ItemList';
import ItemAdder from './ItemAdder';
import ItemsContainer from './ItemsContainer';

export default () => (
  <Subscribe to={[ItemsContainer]}>
    {container => (
      <div>
        <ItemSummary />
        <hr />
        <ItemList />
        <hr />
        <ItemAdder />
      </div>
    )}
  </Subscribe>
);
