import { useEffect } from "react";
import "./css/index.css";
import { API_URL } from "./consts";
import Timer from "./Components/Timer";
import Challenge5 from "./Components/Challenges/Challenge5";
import Button from "./Components/Button";

function App() {
  useEffect(() => {
    fetch(`${API_URL}/puzzleCompleteProp1`)
      .then((res) => res.json())
      .then((data) => {
        console.log(data.completed);
      });
  }, []);

  useEffect(() => {
    fetch(`${API_URL}/puzzleCompleteProp2`)
      .then((res) => res.json())
      .then((data) => {
        console.log(data.completed);
      });
  }, []);

  useEffect(() => {
    fetch(`${API_URL}/puzzleCompleteProp3`)
      .then((res) => res.json())
      .then((data) => {
        console.log(data.completed);
      });
  }, []);

  useEffect(() => {
    fetch(`${API_URL}/puzzleCompleteProp4`)
      .then((res) => res.json())
      .then((data) => {
        console.log(data.completed);
      });
  }, []);

  useEffect(() => {
    fetch(`${API_URL}/puzzleCompleteProp5`)
      .then((res) => res.json())
      .then((data) => {
        console.log(data.completed);
      });
  }, []);

  // useEffect(() => {
  //   fetch(`${API_URL}/restartProp4`)
  //     .then((res) => res.json())
  //     .then((data) => {
  //       console.log(data.completed);
  //     });
  // }, []);

  const restartProp = () => {
    console.log("trying to fetch");
    fetch(`${API_URL}/restartProp4`, {
      method: "GET",
    })
      .then((res) => res.json())
      .then((data) => {
        console.log("completed to fetch");
        console.log(data);
      });
  };

  return (
    <>
      <Timer />
      <Button />
      <Challenge5 />
      <button onClick={restartProp}>restart</button>
    </>
  );
}

export default App;
