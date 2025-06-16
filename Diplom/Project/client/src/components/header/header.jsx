import React, {useEffect, useState} from "react";
import {AppShell, Avatar, Group, Menu, Text} from "@mantine/core";
import {IconLogout, IconUser} from "@tabler/icons-react";
import {useNavigate} from "react-router-dom";
import Store from "../../store/store";
import ThemeSwitcher from "./ThemeSwitcher";
import AdminMenu from "../adminMenu/AdminMenu";
import userLogo from "../../images/user.png";

function Header({logo}) {

  const store = new Store();
  const navigate = useNavigate();
  const [data, setData] = useState([]);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const users = await store.GetUserById();
        setData(users.data);
        await store.checkAuth();
      } catch (error) {
        console.log(error.response);
        if (error.response.data.statusCode === 401) {
          store.logout();
          navigate("/login");
        } else {
          console.log(error.response.data);
        }
      }
    };

    fetchData();
    if (!localStorage.getItem("token")) {
      navigate("/login");
    }
  }, []);

  return (
      <AppShell.Header px={"260"}>
        <Group position="apart" justify={"space-between"} w={"100%"} h={"100%"}>
          <AppShell.Section>
            <AdminMenu>

            <Group onClick={() => navigate("/AdminHome")} style={{ cursor: "pointer" }}>
              <Avatar src={logo} alt="Hm" size="sm" />
              <Text>Hm</Text>
            </Group>
            </AdminMenu>
          </AppShell.Section>
          <Group>
          <ThemeSwitcher />

          <Menu position="bottom-end" withArrow>
            <Menu.Target>
              <Group style={{ cursor: "pointer" }}>
                <Avatar src={userLogo} alt="User Avatar" radius="xl" size="sm" />
                <Text>{localStorage.getItem("name")}</Text>
              </Group>
            </Menu.Target>

            <Menu.Dropdown>
              <Menu.Item
                  icon={<IconUser size="1rem" />}
                  onClick={() => navigate("/AdminProfile")}
              >
                Профиль
              </Menu.Item>

              <Menu.Divider />

              <Menu.Item
                  icon={<IconLogout size="1rem" />}
                  onClick={() => {
                    store.logout()
                    navigate("/login");
                  }}
              >
                Выйти
              </Menu.Item>
            </Menu.Dropdown>
          </Menu>
          </Group>
        </Group>
      </AppShell.Header>
  );
}

export default Header;