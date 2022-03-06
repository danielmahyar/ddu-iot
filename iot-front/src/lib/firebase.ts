// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getDatabase } from "firebase/database";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
const firebaseConfig = {
	apiKey: "AIzaSyCEVmy83es4KlCdI3qKDmXr5eDln0EIRrQ",
	authDomain: "ddu-iot.firebaseapp.com",
	databaseURL: "https://ddu-iot-default-rtdb.europe-west1.firebasedatabase.app",
	projectId: "ddu-iot",
	storageBucket: "ddu-iot.appspot.com",
	messagingSenderId: "651290165877",
	appId: "1:651290165877:web:23ab52b7c59c4cf959ae3c"
};

let app = initializeApp(firebaseConfig);

export const db = getDatabase(app)