import React, { useEffect, useState } from 'react'
import database, { onChildAdded, query, ref } from 'firebase/database'
import { db } from '../lib/firebase';
const AssignHouse = () => {
	const [houses, setHouses] = useState<any[]>([])
	const q = query(ref(db, 'houses'))
	useEffect(() => onChildAdded(q, (dbHouses) => {
		setHouses([...houses, dbHouses])
	}), [])

	return (
		<div>
			House 1 booked: {houses.filter((house) => house.id === 'house-1')[0]?.booked.toString()}
		</div>
	)
}

export default AssignHouse