import { createResource } from 'simple-cache-provider';
import fetch from 'isomorphic-fetch';

export const cacheFetche = createResource(async () => {
  const response = await fetch('http://localhost:5000/api/getSuccessResponse');
  const jsonResponse = await response.json();
  return jsonResponse;
});
