/* eslint-disable react/prefer-stateless-function */
import React, { Component } from 'react';
import { hot } from 'react-hot-loader';

import './App.css';
import Newsletter from './components/Newsletter';


class App extends Component {
  render() {
    return (
      <div className="App">
        <h1> Hello, FancyButton! </h1>
        
      </div>
    );
  }
}

export default hot(module)(App);
