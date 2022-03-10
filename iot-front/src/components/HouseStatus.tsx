import { ref } from 'firebase/database';
import React from 'react'
import { useList } from 'react-firebase-hooks/database';
import { db } from '../lib/firebase';

const HouseStatus = () => {
	const [snapshots, loading, error] = useList(ref(db, 'houses/house-1'));
	const [snapshots2, loading2, error2] = useList(ref(db, 'houses/house-2'));
	console.log({ snapshots, snapshots2 })
	return (
		<section>
			<div>
				{snapshots && snapshots.map(list => {
					const key = list.key
					const data = list.val()
					if(typeof data === 'boolean'){
						return (
							<p>{key}: {data === true ? "true" : "false"}</p>
						)
					}
					return (
						<p>{key}: {data}</p>
					)
				})}
			</div>
			<div>
				{snapshots2 && snapshots2.map(list => {
					const key = list.key
					const data = list.val()
					if(typeof data === 'boolean'){
						return (
							<p>{key}: {data === true ? "true" : "false"}</p>
						)
					}
					return (
						<p>{key}: {data}</p>
					)
				})}
			</div>
		</section>
	)
}

export default HouseStatus