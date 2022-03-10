import React from 'react';
import AssignHouse from './components/AssignHouse';
import HouseStatus from './components/HouseStatus'

function App() {
  return (
    <main className="w-screen h-screen flex flex-col ">

      <nav className="w-full h-12 p-5 bg-yellow flex items-center justify-center">
        <h1 className="text-lg font-bold text-center">VoHouses</h1>
      </nav>

      <section className="w-full h-full">
        <AssignHouse />
        <HouseStatus />
      </section>
    </main>
  );
}

export default App;
