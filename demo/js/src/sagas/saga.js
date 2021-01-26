import { put, takeLatest } from 'redux-saga/effects';
import fetch from 'isomorphic-fetch';

async function request() {
  const response = await fetch('http://localhost:5000/api/getSuccessResponse');
  const json = await response.json();
  return json;
}

export function* fetchList() {
  
  const myListResponse = yield request();
  yield put({ type: 'FETCH_LIST_SUCCEED', list: myListResponse });
}

function* mySaga() {
  yield takeLatest('FETCH_LIST', fetchList);
}

export default mySaga;
