import { useRef, useState, useEffect } from 'react';
import stillframe from './assets/stillframe.jpg';
import animationData from "./assets/data.json";
import Lottie from "lottie-react";

export default function MainScreenAnimation() {
  /* ADD: https://lottiereact.com/hooks/useLottieInteractivity */  

  const lottieRef = useRef();
  const [animDuration, setAnimDuration] = useState(0);

  const options = {
    animationData: animationData,
    loop: false,
    autoplay: true,
  };

  useEffect(() => {
    const timer = setInterval(() => {
      setAnimDuration(animDuration => animDuration + 1);
    }, 1000);
    return () => clearInterval(timer);
  }, [lottieRef]); //useEffect should run only one, but lottieRef will be ommited only once => on mount!
  

  return (
    <div>
      {animDuration >= 13 ? (
        <img src={stillframe} alt="static-after-lottie"/>
        ) : (
          <Lottie
            animationData={options.animationData}
            loop={options.loop}
            autoPlay={options.autoplay}
            lottieRef={lottieRef}
            onDestroy={ //wtf, this events ommits also on the mount... :)))))
              ()=>{console.log("Destroyed!\n");}
            }
          />
      )}
    </div>
  );
}
