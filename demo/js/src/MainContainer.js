import React, { Suspense } from 'react';
import Loader from './Loader';
import ErrorBoundary from './ErrorBoundary';
// import asyncComponent from './AsyncComponent';
// const Artists = React.lazy(()=>import('./Artists'));
const MyCustomList = React.lazy(() => import('./MyCustomList'));
// const ReduxComponent = React.lazy(() => import('./ReduxComponent'));

// const MyFailList = React.lazy(()=> import('./MyFailList'));

// const AsyncMyList = asyncComponent(() => import("./MyList"));

export default function MainContainer() {
  return (
    <div>
      <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          {/* <MyList/> */}
          <MyCustomList />
        </Suspense>
      </ErrorBoundary>
      {/* <ErrorBoundary   >
        <Suspense fallback={<Loader />}>
          <Artists/>
        </Suspense>
      </ErrorBoundary> */}
    </div>
  );
}
