import { useState } from "react";
import { API_URL } from "../consts.js";

export default function Button() {
  const [toggleState, setToggleState] = useState(false);

  const toggle = () => {
    fetch(`${API_URL}/startChallenge1`);
    setToggleState((prev) => !prev);
  };

  // useEffect(() => {
  //   fetch(`${API_URL}/propState`)
  //     .then(res => res.json())
  //     .then(data => {
  //       setToggleState(data.ledState === "off")
  //     })
  // }, []);

  return (
    <>
      {toggleState && (
        <button className="btn-on" onClick={toggle}>
          On
        </button>
      )}
      {!toggleState && (
        <button className="btn-off" onClick={toggle}>
          Off
        </button>
      )}
    </>
  );
}
