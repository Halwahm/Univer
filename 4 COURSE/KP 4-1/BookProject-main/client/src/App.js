import React, { useContext, useState, useEffect } from 'react';
import { BrowserRouter } from 'react-router-dom';
import AppRouter from './components/AppRouter';
import NavBar from './components/NavBar';
import { observer } from 'mobx-react-lite';
import { Context } from './index';
import { check } from './http/userAPI';
import { Spinner } from 'react-bootstrap';
import { Alert } from 'react-bootstrap';

const App = observer(() => {
  const { user } = useContext(Context);
  const [loading, setLoading] = useState(true);

  const [alertshow, setAlertshow] = useState(false);
  const [variant, setVariant] = useState("success");
  const [alertText, setAlertText] = useState("Успешно");

  useEffect(() => {
    setAlertshow(false);
    check().then(data => {
      user.setUser(true);
      user.setIsAuth(true);

    }).catch((e) => {
      if (!e.response) {
      setAlertshow(true);
      setVariant("danger");
      localStorage.removeItem('token');
      localStorage.removeItem('id');
      setAlertText("Cервер вернул ошибку: " + e.message);
      console.log(e);
      }
    }).finally(() => setLoading(false))
  }, [])

  if (loading) {
    return <Spinner animation={'grow'}></Spinner>
  }
  return (
    <BrowserRouter>
      <NavBar />
      {alertshow && (
        <Alert
          variant={variant}
          className="mt-3"
          onClose={() => setAlertshow(false)}
          dismissible
        >
          {alertText}
        </Alert>
      )}
      <AppRouter />
    </BrowserRouter>
  );
}
)
export default App;
