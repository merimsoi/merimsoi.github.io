import React, { Suspense } from 'react';
import Loader from './Loader';
import ErrorBoundary from './ErrorBoundary';
import asyncComponent from './AsyncComponent';

const Artists = React.lazy(() => import('./Artists'));
const MyStateList = React.lazy(() => import('./MyStateList'));
const ReduxComponent = React.lazy(() => import('./ReduxComponent'));
const CacheComponent = React.lazy(() => import('./CacheComponent'));
const MyAsyncStateList = asyncComponent(() => import('./MyStateList'));

// const MyFailList = React.lazy(()=> import('./MyFailList'));

export default function MainContainer() {
  return (
    <div>
      <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <Artists />
        </Suspense>
      </ErrorBoundary>
      <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <MyStateList />
        </Suspense>
      </ErrorBoundary>
      <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <ReduxComponent />
        </Suspense>
      </ErrorBoundary>
      <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <CacheComponent />
        </Suspense>
      </ErrorBoundary>
      <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <MyAsyncStateList />
        </Suspense>
      </ErrorBoundary>
    </div>
  );
}
