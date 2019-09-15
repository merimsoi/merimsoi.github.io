import React from "react";
import ReactDOM from "react-dom";
import App from "./App.js";
import { createStore,applyMiddleware } from 'redux'
import { Provider } from 'react-redux'
import rootReducer from './reducers'
import createSagaMiddleware from 'redux-saga'
import mySaga from './sagas/saga'

const sagaMiddleware = createSagaMiddleware();
const store = createStore(rootReducer,applyMiddleware(sagaMiddleware))
sagaMiddleware.run(mySaga)

ReactDOM.render( 
<Provider store={store}>
    <App />
</Provider>, 
document.getElementById("app-react")
);