import React, { Suspense } from 'react';
import Loader from './Loader';
import ErrorBoundary from './ErrorBoundary';
// import asyncComponent from './AsyncComponent';
// const Artists = React.lazy(() => import('./Artists'));
const CacheComponent = React.lazy(() => import('./CacheComponent'));
// const ReduxComponent = React.lazy(() => import('./ReduxComponent'));

// const MyFailList = React.lazy(()=> import('./MyFailList'));

// const AsyncMyList = asyncComponent(() => import("./MyList"));

export default function MainContainer() {
  return (
    <div>
      {/* <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <Artists />
        </Suspense>
      </ErrorBoundary> */}
      {/* <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <MyList />
        </Suspense>
      </ErrorBoundary> */}
      <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <CacheComponent />
        </Suspense>
      </ErrorBoundary>
    </div>
  );
}
