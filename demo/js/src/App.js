/* eslint-disable react/prefer-stateless-function */
import React, { Component } from 'react';
import { hot } from 'react-hot-loader';
import MainContainer from './MainContainer';
import './App.css';

class App extends Component {
  render() {
    return (
      <div className="App">
        <h1> Hello, Lazy React Loading! </h1>
        <MainContainer />
      </div>
    );
  }
}

export default hot(module)(App);
