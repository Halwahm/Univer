import {AppShell} from '@mantine/core';
import Header from '../components/header/header';
import {Outlet} from "react-router-dom";
import logo from "../images/logo.png";

export function MainLayout() {
    return (
        <AppShell
            header={{ height: 60 }}
            navbar={{
                width: 260,
                breakpoint: 'sm',
            }}
            aside={{
                width: 260,
                breakpoint: 'sm',
            }}
            padding="md"
        >
            <Header logo={logo}/>
            <AppShell.Navbar></AppShell.Navbar>
            <AppShell.Aside></AppShell.Aside>

            <AppShell.Main h={"100%"}>
                <Outlet />
            </AppShell.Main>
        </AppShell>
    );
} 