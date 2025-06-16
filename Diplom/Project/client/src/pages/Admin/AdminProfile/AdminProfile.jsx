/* eslint-disable default-case */
/* eslint-disable jsx-a11y/heading-has-content */
/* eslint-disable jsx-a11y/anchor-is-valid */
import React, {useEffect, useState} from "react";
import {
  Avatar,
  Badge,
  Button,
  Card,
  Container,
  Divider,
  Grid,
  Group,
  Image,
  LoadingOverlay,
  Modal,
  Paper,
  PasswordInput,
  Stack,
  Table,
  Text,
  TextInput,
  Title,
  useMantineTheme
} from "@mantine/core";
import {IconArrowBackUp, IconCheck, IconLock, IconMail, IconQrcode, IconUser, IconX} from "@tabler/icons-react";
import Store from "../../../store/store";
import logo from "../../../images/user.png";
import {notifications} from "@mantine/notifications";
import {ToastContainer} from "react-toastify";

const AdminProfile = () => {
  const store = new Store();
  const theme = useMantineTheme();
  const [loading, setLoading] = useState(true);
  const [userData, setUserData] = useState(null);
  const [tickets, setTickets] = useState([]);
  const [data, setData] = useState([]);
  const [dataTicket, setDataTicket] = useState([]);
  const [confirmationValue1, setConfirmationValue1] = useState(undefined);
  const [confirmationValue2, setConfirmationValue2] = useState(undefined);
  const [confirmationValue3, setConfirmationValue3] = useState(undefined);
  const [confirmationValue4, setConfirmationValue4] = useState(undefined);
  const [formData, setFormData] = useState({
    name: "",
    email: "",
    password: "",
  });

  const setConfirmationButtonValues = (value1, value2, value3) => {
    setConfirmationValue1(value1);
    setConfirmationValue2(value2);
    setConfirmationValue3(value3);
  };

  const setConfirmationButtonValuess = (value1) => {
    setConfirmationValue4(value1);
  };

  useEffect(() => {
    const fetchUserData = async () => {
      try {
        const response = await store.GetUserById();
        setUserData(response.data);
        setFormData({
          name: response.data.name || "",
          email: response.data.email || "",
          password: "",
        });
      } catch (error) {
        notifications.show({
          title: 'Ошибка',
          message: 'Не удалось загрузить данные пользователя',
          color: 'red',
        });
      }
    };

    const fetchTickets = async () => {
      try {
        const response = await store.GetTicketUser();
        setTickets(response.data);
      } catch (error) {
        notifications.show({
          title: 'Ошибка',
          message: 'Не удалось загрузить билеты',
          color: 'red',
        });
      }
    };

    const fetchData = async () => {
      try {
        const [users, tickets] = await Promise.all([
          store.GetUserById(),
          store.GetTicketUser()
        ]);
        setData(users.data);
        setDataTicket(tickets.data);
        setFormData({
          name: users.data.name || "",
          email: users.data.email || "",
          password: "",
        });
      } catch (error) {
        notifications.show({
          title: 'Ошибка',
          message: 'Не удалось загрузить данные',
          color: 'red',
        });
      } finally {
        setLoading(false);
      }
    };

    fetchUserData();
    fetchTickets();
    fetchData();
  }, []);

  const handleChange = (e) => {
    setFormData(prev => ({ ...prev, [e.target.id]: e.target.value }));
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    setLoading(true);

    try {
      const response = await store.ChangeUserInfo(formData);
      setUserData(response.data);
      localStorage.setItem("name", response.data.name);

      notifications.show({
        title: 'Успех',
        message: 'Данные успешно обновлены',
        color: 'green',
        icon: <IconCheck size="1rem" />,
      });
    } catch (error) {
      const errorMessage = error.response?.data?.message || 'Произошла ошибка при обновлении данных';

      notifications.show({
        title: 'Ошибка',
        message: errorMessage,
        color: 'red',
        icon: <IconX size="1rem" />,
      });
    } finally {
      setLoading(false);
    }
  };

  const handleDeleteTicket = async () => {
    try {
      const res = await store.DeleteTicket(
        confirmationValue1,
        confirmationValue2,
        confirmationValue3
      );
      setDataTicket(res.data);
      notifications.show({
        title: 'Успех',
        message: 'Билет успешно возвращен',
        color: 'green',
      });
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось вернуть билет',
        color: 'red',
      });
    }
  };

  if (loading) {
    return (
      <>
        <ToastContainer />
            <Container size="xl" py="xl">
              <LoadingOverlay visible={true} />
            </Container>

      </>
    );
  }

  return (
    <>
      <ToastContainer />


          <Container size="xl" py="xl">
            <Stack spacing="xl">
              <Group position="apart">
                <Title order={2}>Профиль {userData?.name}</Title>
                <Badge size="lg" variant="light">
                  {userData?.status}
                </Badge>
              </Group>

              <Grid>
                {/* Левая колонка с информацией о пользователе */}
                <Grid.Col span={4}>
                  <Stack>
                  <Card shadow="sm" padding="lg" radius="md" withBorder>
                    <Stack align="center" spacing="md">
                      <Avatar
                        src={logo}
                        size={120}
                        radius={120}
                        mx="auto"
                      />
                      <Text size="xl" weight={500}>{userData?.name}</Text>
                      <Text size="sm" color="dimmed">{userData?.email}</Text>
                    </Stack>

                    <Divider my="md" />

                    <Stack spacing="xs">
                      <Group>
                        <IconUser size="1rem" />
                        <Text>Имя: {userData?.name}</Text>
                      </Group>
                      <Group>
                        <IconMail size="1rem" />
                        <Text>Email: {userData?.email}</Text>
                      </Group>
                    </Stack>
                  </Card>
                    <Card shadow="sm" padding="lg" radius="md" withBorder>
                      <LoadingOverlay visible={loading} />

                      <Title order={3} mb="md">Изменение данных</Title>

                      <form onSubmit={handleSubmit}>
                        <Stack spacing="md">
                          <TextInput
                              label="Имя"
                              placeholder="Введите ваше имя"
                              id="name"
                              value={formData.name}
                              onChange={handleChange}
                              icon={<IconUser size="1rem" />}
                              required
                          />

                          <TextInput
                              label="Email"
                              placeholder="Введите ваш email"
                              id="email"
                              value={formData.email}
                              onChange={handleChange}
                              icon={<IconMail size="1rem" />}
                              required
                          />

                          <PasswordInput
                              label="Пароль"
                              placeholder="Введите новый пароль"
                              id="password"
                              value={formData.password}
                              onChange={handleChange}
                              icon={<IconLock size="1rem" />}
                              minLength={6}
                          />

                          <Group position="right" mt="md">
                            <Button
                                type="submit"
                                loading={loading}
                                leftIcon={<IconCheck size="1rem" />}
                            >
                              Сохранить изменения
                            </Button>
                          </Group>
                        </Stack>
                      </form>
                    </Card>
                  </Stack>
                </Grid.Col>

                {/* Правая колонка с формой редактирования */}
                <Grid.Col span={8}>


                  <Paper p="md" radius="md" withBorder>
                    <Title order={3} mb="md">Ваши заказы</Title>
                    <Table striped highlightOnHover withColumnBorders>
                      <Table.Thead>
                        <Table.Tr>
                          <Table.Th>Фильм</Table.Th>
                          <Table.Th>Дата</Table.Th>
                          <Table.Th>Время</Table.Th>
                          <Table.Th>Зал</Table.Th>
                          <Table.Th>Место</Table.Th>
                          <Table.Th>QR-код</Table.Th>
                          <Table.Th>Вернуть</Table.Th>
                        </Table.Tr>
                      </Table.Thead>
                      <Table.Tbody>
                        {dataTicket?.map((item) => (
                          <Table.Tr key={item.id}>
                            <Table.Td>{item.session?.film.name}</Table.Td>
                            <Table.Td>
                              {new Date(item.session?.dateSession)
                                .getDate()
                                .toString()
                                .padStart(2, "0")}
                              .
                              {(new Date(item.session?.dateSession).getMonth() + 1)
                                .toString()
                                .padStart(2, "0")}
                              .
                              {new Date(item.session?.dateSession)
                                .getFullYear()
                                .toString()}
                            </Table.Td>
                            <Table.Td>
                              {String(
                                new Date("2023-12-11T" + item.session?.timeSession)
                                  .getHours()
                              ).padStart(2, "0")}
                              :
                              {String(
                                new Date("2023-12-11T" + item.session?.timeSession)
                                  .getMinutes()
                              ).padStart(2, "0")}
                            </Table.Td>
                            <Table.Td>{item.session?.hall.name}</Table.Td>
                            <Table.Td>{item.place?.place}</Table.Td>
                            <Table.Td>
                              <Button
                                variant="light"
                                color="blue"
                                onClick={() => setConfirmationButtonValuess(item.QR)}
                                leftIcon={<IconQrcode size="1rem" />}
                              >
                                QR-код
                              </Button>
                            </Table.Td>
                            <Table.Td>
                              <Button
                                variant="light"
                                color="red"
                                onClick={() => {
                                  if (item.status !== "DisActive") {
                                    setConfirmationButtonValues(
                                      item.id,
                                      item.chatr_id,
                                      item.coast_set
                                    );
                                  }
                                }}
                                disabled={item.status === "DisActive"}
                              >
                                <IconArrowBackUp />
                              </Button>
                            </Table.Td>
                          </Table.Tr>
                        ))}
                      </Table.Tbody>
                    </Table>
                  </Paper>
                </Grid.Col>
              </Grid>
            </Stack>
          </Container>


        <Modal
          opened={!!confirmationValue1}
          onClose={() => setConfirmationButtonValues(undefined, undefined, undefined)}
          title="Подтверждение"
          size="sm"
        >
          <Stack spacing="md">
            <Text>Вы уверены что хотите вернуть билет?</Text>
            <Group position="right" spacing="xs">
              <Button
                variant="default"
                onClick={() => setConfirmationButtonValues(undefined, undefined, undefined)}
              >
                Отмена
              </Button>
              <Button
                color="blue"
                onClick={() => {
                  handleDeleteTicket();
                  setConfirmationButtonValues(undefined, undefined, undefined);
                }}
              >
                Вернуть
              </Button>
            </Group>
          </Stack>
        </Modal>

        <Modal
          opened={!!confirmationValue4}
          onClose={() => setConfirmationButtonValuess(undefined)}
          title="QR-код билета"
          size="sm"
          centered
        >
          <Stack spacing="md">
            <Image
              src={confirmationValue4}
              alt="QR-код билета"
              radius="md"
              style={{ maxWidth: '100%', height: 'auto' }}
            />
            <Text align="center" size="sm" color="dimmed">
              Предъявите QR-код контроллеру
            </Text>
            <Button
              variant="default"
              onClick={() => setConfirmationButtonValuess(undefined)}
              fullWidth
            >
              Закрыть
            </Button>
          </Stack>
        </Modal>

        </>
  );
};

export default AdminProfile;
