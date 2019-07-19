import React, { Suspense } from 'react';
import Loader from './Loader';
import ErrorBoundary from './ErrorBoundary';

// const ArtistComponent = React.lazy(() => import('./ArtistComponent'));
const Artists = React.lazy(() => import('./Artists'));
// const Reject = React.lazy(() => import('./Reject'));


export default function MainContainer() {
  return (
    <div>
      <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <Artists />
        </Suspense>
      </ErrorBoundary>
    </div>
  );
}
