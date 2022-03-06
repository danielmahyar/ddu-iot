import React from 'react';
import AssignHouse from './components/AssignHouse';
import HouseStatus from './components/HouseStatus'

function App() {
  return (
    <main className="w-screen h-screen flex flex-col bg-slate-600">
      <div>

        <nav className="w-full h-8 bg-black">

        </nav>

      </div>
      <section className="flex w-full h-full">
          <aside className="w-16 flex-shrink-0 h-full bg-black">
            w
          </aside>
          <main className="w-full h-full">
              <HouseStatus />
              <AssignHouse />
          </main>
      </section>
    </main>
  );
}

export default App;
