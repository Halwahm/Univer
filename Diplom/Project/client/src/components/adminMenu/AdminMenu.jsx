import React, {useEffect, useState} from "react";
import {
  Divider,
  Group,
  HoverCard,
  Stack,
  Text,
  UnstyledButton,
  useMantineTheme,
} from "@mantine/core";
import {
  IconBuilding,
  IconCalendar,
  IconChartBar,
  IconDeviceTv,
  IconFile,
  IconHeart,
  IconHistory,
  IconHome,
  IconList,
  IconLogout,
  IconUser,
  IconVideo
} from "@tabler/icons-react";
import {useLocation, useNavigate} from "react-router-dom";
import Store from "../../store/store";

const AdminMenu = ({ children }) => {
  const store = new Store();
  const [data, setData] = useState([]);
  const navigate = useNavigate();
  const location = useLocation();
  const theme = useMantineTheme();

  useEffect(() => {
    const fetchData = async () => {
      try {
        const users = await store.GetUserById();
        setData(users.data);
      } catch (error) {
        if (error.response.data.message === "Пользователь не авторизован") {
          await store.logout();
          navigate("/login");
        } else {
          console.log(error.response.data);
        }
      }
    };
    fetchData();
  }, []);

  const handleLogout = () => {
    store.logout();
    navigate("/login");
  };

  const adminMenuItems = [
    {
      icon: IconVideo,
      items: [
        { label: "Кинотека", link: "/AdminHome", icon: IconVideo },
        { label: "Любимые", link: "/AdminFavourite", icon: IconHeart },
      ],
    },
    {
      icon: IconUser,
      items: [
        { label: "Пользователи", link: "/AdminAllUsers", icon: IconUser },
        { label: "Жанры", link: "/AdminGenre", icon: IconList },
        { label: "Добавить фильм", link: "/AdminAddFilm", icon: IconFile },
        { label: "Добавить зал", link: "/AdminAddHall", icon: IconBuilding },
        { label: "Добавить сеанс", link: "/AdminAddSession", icon: IconCalendar },
      ],
    },
    {
      icon: IconFile,
      items: [
        { label: "Все фильмы", link: "/AdminAllFilm", icon: IconFile },
        { label: "Все сеансы", link: "/AdminAllSession", icon: IconCalendar },
        { label: "История действий", link: "/History", icon: IconHistory },
        { label: "Контроллер", link: "/Controller", icon: IconDeviceTv },
      ],
    },
    {
      icon: IconChartBar,
      items: [
        { label: "Статистика", link: "/AdminStatistic", icon: IconChartBar },
      ],
    },
  ];

  const userMenuItems = [
    {
      icon: IconVideo,
      items: [
        { label: "Кинотека", link: "/AdminHome", icon: IconVideo },
        { label: "Любимые", link: "/AdminFavourite", icon: IconHeart },
        { label: "Жанры", link: "/AdminGenre", icon: IconList },
      ],
    },
  ];

  const menuItems = data.role === "Admin" ? adminMenuItems : userMenuItems;

  const isActive = (link) => location.pathname === link;

  return (
    <HoverCard width={300} position="bottom" shadow="md">
      <HoverCard.Target>
        {/*<Button*/}
        {/*  variant="subtle"*/}
        {/*  rightIcon={<IconChevronDown size={16} />}*/}
        {/*  leftIcon={<IconVideo size={20} />}*/}
        {/*>*/}
        {/*  Меню*/}
        {/*</Button>*/}
        {children}
      </HoverCard.Target>

      <HoverCard.Dropdown>
        <Stack spacing="md">
          <UnstyledButton 
            onClick={() => navigate("/AdminHome")} 
            sx={(theme) => ({
              display: 'block',
              width: '100%',
              padding: theme.spacing.xs,
              borderRadius: theme.radius.sm,
              color: isActive("/AdminHome") 
                ? theme.colors[theme.primaryColor][6]
                : theme.colorScheme === 'dark' ? theme.colors.dark[0] : theme.black,
              backgroundColor: isActive("/AdminHome")
                ? theme.fn.rgba(theme.colors[theme.primaryColor][6], 0.1)
                : 'transparent',
              '&:hover': {
                backgroundColor: isActive("/AdminHome")
                  ? theme.fn.rgba(theme.colors[theme.primaryColor][6], 0.15)
                  : theme.colorScheme === 'dark' ? theme.colors.dark[6] : theme.colors.gray[0],
              },
            })}
            size="sm" 
            fw={700}
          >
            <Group spacing="xs">
              <IconHome 
                size={16} 
                color={isActive("/AdminHome") ? theme.colors[theme.primaryColor][6] : undefined}
              />
              <Text 
                size="sm"
                color={isActive("/AdminHome") ? theme.colors[theme.primaryColor][6] : undefined}
              >
                Главная
              </Text>
            </Group>
          </UnstyledButton>

          {menuItems.map((section) => (
            <Stack key={section.items.label} spacing="xs">
              <Divider />
              {section.items.map((item) => (
                <UnstyledButton
                  key={item.label}
                  onClick={() => navigate(item.link)}
                  sx={(theme) => ({
                    display: 'block',
                    width: '100%',
                    padding: theme.spacing.xs,
                    borderRadius: theme.radius.sm,
                    color: isActive(item.link)
                      ? theme.colors[theme.primaryColor][6]
                      : theme.colorScheme === 'dark' ? theme.colors.dark[0] : theme.black,
                    backgroundColor: isActive(item.link)
                      ? theme.fn.rgba(theme.colors[theme.primaryColor][6], 0.1)
                      : 'transparent',
                    '&:hover': {
                      backgroundColor: isActive(item.link)
                        ? theme.fn.rgba(theme.colors[theme.primaryColor][6], 0.15)
                        : theme.colorScheme === 'dark' ? theme.colors.dark[6] : theme.colors.gray[0],
                    },
                  })}
                >
                  <Group spacing="xs">
                    <item.icon 
                      size={16} 
                      color={isActive(item.link) ? theme.colors[theme.primaryColor][6] : undefined}
                    />
                    <Text 
                      size="sm"
                      color={isActive(item.link) ? theme.colors[theme.primaryColor][6] : undefined}
                    >
                      {item.label}
                    </Text>
                  </Group>
                </UnstyledButton>
              ))}
            </Stack>
          ))}
          <Divider />
          <UnstyledButton
            onClick={handleLogout}
            sx={(theme) => ({
              display: 'block',
              width: '100%',
              padding: theme.spacing.xs,
              borderRadius: theme.radius.sm,
              color: theme.colors.red[6],
              '&:hover': {
                backgroundColor: theme.colorScheme === 'dark' ? theme.colors.dark[6] : theme.colors.gray[0],
              },
            })}
          >
            <Group spacing="xs">
              <IconLogout size={16} />
              <Text size="sm">Выйти</Text>
            </Group>
          </UnstyledButton>
        </Stack>
      </HoverCard.Dropdown>
    </HoverCard>
  );
};

export default AdminMenu; 