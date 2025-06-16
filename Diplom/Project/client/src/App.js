import {BrowserRouter, Navigate, Route, Routes} from "react-router-dom";
import {MantineProvider} from "@mantine/core";
import Login from "./pages/login/Login";
import Registration from "./pages/registration/Registration";
import AdminAddFilm from "./pages/Admin/AdminAddFilm/AdminAddFilm";
import AdminAddHall from "./pages/Admin/AdminAddHall/AdminAddHall";
import AdminAddSession from "./pages/Admin/AdminAddSession/AdminAddSession";
import AdminAllFilm from "./pages/Admin/AdminAllFilm/AdminAllFilm";
import AdminAllUsers from "./pages/Admin/AdminAllUsers/AdminAllUsers";
import AdminFavourite from "./pages/Admin/AdminFavourite/AdminFavourite";
import AdminGenre from "./pages/Admin/AdminGenre/AdminGenre";
import AdminHome from "./pages/Admin/AdminHome/AdminHome";
import AdminProfile from "./pages/Admin/AdminProfile/AdminProfile";
import Film from "./pages/Admin/Film/Film";
import GenreFilm from "./pages/Admin/GenreFilm/GenreFilm";
import History from "./pages/Admin/History/History";
import AdminStatistic from "./pages/Admin/AdminStatistic/AdminStatistic";
import AdminAllSession from "./pages/Admin/AdminAllSession/AdminAllSession";
import TheController from "./pages/Admin/Сontroller/Controllers";

import "@mantine/core/styles.css";
import '@mantine/notifications/styles.css';
import '@mantine/carousel/styles.css';

import {MainLayout} from "./layouts/MainLayout";
import {Notifications} from "@mantine/notifications";
import AdminAllHall from "./pages/Admin/AdminAllHall/AdminAllHall";

function App() {
    return (
      <MantineProvider
        defaultColorScheme="light"
        theme={{
            primaryColor: "teal",
            fontFamily: 'Inter, sans-serif',
        }}
      >
          <Notifications/>
          <BrowserRouter>
              <Routes>
                  {/* Auth routes */}
                  <Route path="/login" element={<Login />} />
                  <Route path="/register" element={<Registration />} />
                  
                  {/* Protected admin routes */}
                  <Route path="/" element={<MainLayout />}>
                      <Route index element={<Navigate to="/AdminHome" replace />} />
                      <Route path="AdminHome" element={<AdminHome />} />
                      <Route path="AdminAddFilm" element={<AdminAddFilm />} />
                      <Route path="AdminAddHall" element={<AdminAddHall />} />
                      <Route path="AdminAddSession" element={<AdminAddSession />} />
                      <Route path="AdminAllFilm" element={<AdminAllFilm />} />
                      <Route path="AdminAllHall" element={<AdminAllHall />}></Route>
                      <Route path="AdminAllUsers" element={<AdminAllUsers />} />
                      <Route path="AdminFavourite" element={<AdminFavourite />} />
                      <Route path="AdminGenre" element={<AdminGenre />} />
                      <Route path="History" element={<History />} />
                      <Route path="AdminProfile" element={<AdminProfile />} />
                      <Route path="FilmGenre" element={<GenreFilm />} />
                      <Route path="Film" element={<Film />} />
                      <Route path="AdminStatistic" element={<AdminStatistic />} />
                      <Route path="AdminAllSession" element={<AdminAllSession />} />
                      <Route path="Controller" element={<TheController />} />
                  </Route>
              </Routes>
          </BrowserRouter>
      
      </MantineProvider>
    );
}

export default App;