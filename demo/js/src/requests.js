import fetch from 'isomorphic-fetch';

const request = async () => {
  console.log('I am request from file');
  const response = await fetch('http://localhost:5000/api/getSuccessResponse');
  const json = await response.json();
  console.log(json);
  return json;
};

export default { request };
