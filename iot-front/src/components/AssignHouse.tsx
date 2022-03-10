import React, { useState } from 'react'
import { ref, set } from 'firebase/database'
import { db } from '../lib/firebase';
import { toast } from 'react-hot-toast'
import HouseChoose from './HouseChoose';
const AssignHouse = () => {
	const [booked, setBooked] = useState<any>({ house: null, booked: false, code: null });
	const setPass = async (id: number) => {
		const toastLoad = toast.loading("Booking...");
		const password = Math.floor(1000 + Math.random() * 9000);

		const path = `houses/house-${id}/password`;
		const reference = ref(db, path)
		try {
			await set(reference, password.toString())
			toast.dismiss(toastLoad)
			toast.success("Successfully booked house " + id, { duration: 3000 })
			setBooked({ house: id, booked: true, code: password.toString() })
		} catch (error: any) {
			toast.dismiss(toastLoad)
			toast.error(error.message, { duration: 3000 })
		}

	}
	return (
		<article className="p-4">
			<h2 className="text-2xl font-semibold mb-2">Choose a house:</h2>

			{booked.booked === true ? (
				<div className="w-full h-36 flex flex-col items-center justify-center bg-yellow">
					<p className="font-bold">Booked house {booked.house}</p>
					<div className="px-2">
						<svg className="checkmark" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 52 52">
							<circle className="checkmark__circle" cx="26" cy="26" r="25" fill="none" />
							<path className="checkmark__check" fill="none" d="M14.1 27.2l7.1 7.2 16.7-16.8" />
						</svg>
					</div>
					<p>Your password is {booked.code}</p>
				</div>
			) : (
				<div className="flex flex-col md:flex-row">
					<HouseChoose setPass={setPass} id={1} />
					<HouseChoose setPass={setPass} id={2} />
				</div>
			)}

		</article>
	)
}

export default AssignHouse