import React from 'react'
const HouseChoose = ({ id, setPass }: { id: number, setPass: (id: number) => void }) => {

	return (
		<div className="w-full h-48 border space-y-4 flex flex-col items-center justify-center bg-yellow">
			<p className="font-bold">House {id}</p>
			<button onClick={() => setPass(id)} className="px-4 py-2 bg-white rounded-lg">Click here to book house</button>
		</div>
	)
}

export default HouseChoose