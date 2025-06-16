/* eslint-disable jsx-a11y/heading-has-content */
/* eslint-disable jsx-a11y/anchor-is-valid */
import React, {useEffect, useState} from "react";
import {
  ActionIcon,
  Button,
  Center,
  Container,
  Divider,
  Grid,
  Group,
  LoadingOverlay,
  Modal,
  Paper,
  Stack,
  Table,
  Text,
  TextInput,
  Title,
  useMantineTheme,
} from "@mantine/core";
import {IconCalendar, IconTrash} from "@tabler/icons-react";
import {useLocation} from "react-router-dom";
import {notifications} from "@mantine/notifications";
import Store from "../../../store/store";
import DataFilm from "../../../components/DataFilm/DataFilm";
import {toast, ToastContainer} from "react-toastify";
import "react-toastify/dist/ReactToastify.css";

const Film = () => {
  const theme = useMantineTheme();
  const store = new Store();
  const location = useLocation();
  const searchParams = new URLSearchParams(location.search);
  const id = searchParams.get("ID");
  searchParams.delete("ID");

  const IdFilm = id || location.state.ID;
  
  const [loading, setLoading] = useState(true);
  const [data, setData] = useState([]);
  const [dataFilms, setDataFilms] = useState(null);
  const [dataFavorite, setDataFavorite] = useState([]);
  const [dataGenre, setDataGenre] = useState(null);
  const [dataImage, setDataImage] = useState([]);
  const [dataSession, setDataSession] = useState([]);
  const [dataPlaces, setDataPlaces] = useState([]);
  const [selectedSession, setSelectedSession] = useState(null);
  const [selectedSeats, setSelectedSeats] = useState([]);
  const [totalPrice, setTotalPrice] = useState(0);
  const [orderModal, setOrderModal] = useState(false);
  const [orderForm, setOrderForm] = useState({
    name: "",
    email: "",
    phone: "",
  });
  const [selectedSeatsInfo, setSelectedSeatsInfo] = useState([]);
  const [addModal, setAddModal] = useState(false);
  const [editModal, setEditModal] = useState(null);
  const [deleteModal, setDeleteModal] = useState(null);

  const fetchFavorite = async () => {
    try {
      const fav = await store.GetFavoriteFilm();
      const currentFilmFavorites = fav.data.filter(fav => fav.film.id === IdFilm);
      setDataFavorite(currentFilmFavorites);
    } catch (error) {
      console.error('Error fetching favorites:', error);
    }
  };

  useEffect(() => {
    const fetchData = async () => {
      try {
        const [filmRes, favRes, userRes] = await Promise.all([
          store.GetDataFilm(IdFilm),
          store.GetFavoriteFilm(),
          store.GetUserById(),
        ]);

        if (localStorage.getItem("errorTicket")) {
          toast(`Сожалею, но данные места уже куплены билеты: ${localStorage.getItem("errorTicket")}`);
          localStorage.removeItem("errorTicket");
        }

        setData(userRes.data);
        // Фильтруем избранные фильмы для текущего фильма
        const currentFilmFavorites = favRes.data.filter(fav => fav.film.id === IdFilm);
        setDataFavorite(currentFilmFavorites);
        setDataFilms(filmRes.data.films);
        setDataGenre(filmRes.data.films.genre);
        setDataImage(filmRes.data.films.img.data);
        setDataSession(filmRes.data.sessions);
        setDataPlaces(filmRes.data.places || []);
      } catch (error) {
        console.error('Error fetching data:', error);
        notifications.show({
          title: 'Ошибка',
          message: 'Не удалось загрузить данные о фильме',
          color: 'red',
        });
      } finally {
        setLoading(false);
      }
    };
    fetchData();
  }, [IdFilm]);

  const handleSessionSelect = async (session) => {
    setSelectedSession(session);
    setSelectedSeats([]);
    setSelectedSeatsInfo([]);
    setTotalPrice(0);
    
    try {
      const userFilmsSession = await store.GetUserIntoSession(session.id);
      setDataPlaces(userFilmsSession.data || []);
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось загрузить данные о сеансе',
        color: 'red',
      });
    }
  };

  const handleSeatSelect = (seat, row, price) => {
    const isOccupied = dataPlaces?.some(item => item.place.place === seat) || false;
    if (isOccupied) return;

    const isSelected = selectedSeats.some(s => s.seat === seat);
    if (isSelected) {
      setSelectedSeats(selectedSeats.filter(s => s.seat !== seat));
      setSelectedSeatsInfo(selectedSeatsInfo.filter(s => s.seat !== seat));
      setTotalPrice(prev => prev - price);
    } else {
      const seatType = price === selectedSession.hall.type_Plase.cost_normal ? "Standart" : "VIP";
      setSelectedSeats([...selectedSeats, { seat, row, price }]);
      setSelectedSeatsInfo([...selectedSeatsInfo, {
        seat,
        row,
        type: seatType,
        price
      }]);
      setTotalPrice(prev => prev + price);
    }
  };

  const handleOrderSubmit = async () => {
    try {
      const tickets = selectedSeats.map(s => s.seat);
      const coast_set = selectedSeats.map(s => s.price);
      
      const tickorder = await store.BuyTicket(
        tickets,
        selectedSession.id,
        IdFilm,
        totalPrice,
        coast_set
      );

      if (Array.isArray(tickorder.data)) {
        const data = tickorder.data.map(item => item.place.place);
        if (data.length !== 0) {
          localStorage.setItem("errorTicket", data.join(', '));
          window.location.reload();
        }
      } else {
        window.location.href = tickorder.data;
      }
      
      setOrderModal(false);
      setSelectedSeats([]);
      setSelectedSeatsInfo([]);
      setTotalPrice(0);
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось оформить заказ',
        color: 'red',
      });
    }
  };

  const handleDeleteOrder = async (id, idsession, coast_set, chatr_id) => {
    try {
      const neworder = await store.Dellorder(id, idsession, coast_set, chatr_id);
      setDataPlaces(neworder.data);
      notifications.show({
        title: 'Успех',
        message: 'Заказ успешно удален',
        color: 'green',
      });
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось удалить заказ',
        color: 'red',
      });
    }
  };

  const isVipSeat = (row, seat, totalRows, totalSeats) => {
    const vipRows = Math.max(2, Math.floor(totalRows / 3));
    const vipSeats = Math.max(2, Math.floor(totalSeats / 3));

    const startRow = Math.floor((totalRows - vipRows) / 2) + 1;
    const endRow = startRow + vipRows - 1;
    const startSeat = Math.floor((totalSeats - vipSeats) / 2) + 1;
    const endSeat = startSeat + vipSeats - 1;

    // Проверяем, находится ли место в VIP секции
    return row >= startRow && row <= endRow && seat >= startSeat && seat <= endSeat;
  };

  const renderSeats = () => {
    if (!selectedSession) return null;

    const rows = Math.ceil(selectedSession.hall.count_rows);
    const seats = [];

    for (let row = 1; row <= rows; row++) {
      const rowSeats = [];
      for (let seat = 1; seat <= selectedSession.hall.count_place; seat++) {
        const seatNumber = (row - 1) * selectedSession.hall.count_place + seat;
        const isOccupied = dataPlaces?.some(item => item.place.place === seatNumber) || false;
        const isSelected = selectedSeats.some(s => s.seat === seatNumber);
        
        // Определяем тип места (VIP или обычное)
        const isVip = isVipSeat(row, seat, rows, selectedSession.hall.count_place);
        const price = isVip ? selectedSession.hall.type_Plase.cost_vip : selectedSession.hall.type_Plase.cost_normal;

        rowSeats.push(
          <Button
            key={seatNumber}
            variant={isOccupied ? "filled" : isSelected ? "filled" : "outline"}
            color={isOccupied ? "gray" : isSelected ? "blue" : isVip ? "yellow" : "blue"}
            onClick={() => !isOccupied && handleSeatSelect(seatNumber, row, price)}
            disabled={isOccupied}
            style={{ width: 40, height: 40, padding: 0 }}
          >
            {seatNumber}
          </Button>
        );
      }
      seats.push(
        <Group w={"100%"} key={row} justify="space-between" mb="xs">
          <Text size="sm" >Ряд {row}</Text>
          {rowSeats}
        </Group>
      );
    }

    return (
      <Paper p="md" radius="md" withBorder>
        <Center>
          <Stack spacing="xs" style={{ width: '100%', maxWidth: '800px' }}>
            <div style={{ display: 'flex', justifyContent: 'center' }}>
              <div style={{ width: "100%", display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
                {seats}
              </div>
            </div>
            {selectedSeatsInfo && selectedSeatsInfo.length > 0 && (
              <Paper p="md" radius="md" withBorder mt="md">
                <Title order={5} mb="xs">Выбранные места:</Title>
                <Grid>
                  {selectedSeatsInfo.map((seat) => (
                    <Grid.Col key={seat.seat} span={4}>
                      <Paper p="xs" radius="md" withBorder>
                        <Text size="sm">Ряд: {seat.row}</Text>
                        <Text size="sm">Место: {seat.seat}</Text>
                        <Text size="sm">Тип: {seat.type}</Text>
                        <Text size="sm">Цена: {seat.price} ₽</Text>
                      </Paper>
                    </Grid.Col>
                  ))}
                </Grid>
              </Paper>
            )}
            <Group position="apart" mt="md">
              <Group spacing="xs">
                <Button variant="outline" color="blue" size="xs">Обычные места</Button>
                <Button variant="outline" color="yellow" size="xs">VIP места</Button>
                <Button variant="filled" color="gray" size="xs">Занятые места</Button>
              </Group>
              <Button 
                color="blue" 
                disabled={selectedSeats.length === 0}
                onClick={() => setOrderModal(true)}
              >
                Оформить заказ ({totalPrice} ₽)
              </Button>
            </Group>
          </Stack>
        </Center>
      </Paper>
    );
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

  if (!dataFilms) {
    return (
      <>
        <ToastContainer />
        
            <Container size="xl" py="xl">
              <Text size="xl" color="red">Фильм не найден</Text>
            </Container>
          
      </>
    );
  }

  return (
    <>
      <ToastContainer />

          <Container size="xl" py="xl">
            <Stack spacing="xl">
              {dataFilms.genre !== null && (
                        <DataFilm
                          data={dataFilms}
                          dataName={dataGenre}
                          dataImage={dataImage}
                          dataFavorite={dataFavorite}
                          onFavoriteChange={fetchFavorite}
                        />
              )}
              
              <Paper p="md" radius="md" withBorder>
                <Title order={3} mb="md" align="center">Доступные сеансы</Title>
                <Group spacing="xs" mb="md">
                  {dataSession.map((session) => (
                    <Button
                      key={session.id}
                      variant={selectedSession?.id === session.id ? "filled" : "outline"}
                      onClick={() => handleSessionSelect(session)}
                      leftIcon={<IconCalendar size="1rem" />}
                    >
                      {new Date(session.dateSession).toLocaleDateString()} {session.timeSession}
                    </Button>
                  ))}
                </Group>

                {selectedSession && (
                  <>
                    <Divider />
                    <Title order={4} my="md">Выберите места</Title>
                    {renderSeats()}
                  </>
                )}
              </Paper>

              {data.role === "Admin" && (
                <Paper p="md" radius="md" withBorder>
                  <Title order={3} mb="md" align="center">Пользователи</Title>
                  <Table striped highlightOnHover>
                    <Table.Thead>
                      <Table.Tr>
                        <Table.Th>Email</Table.Th>
                        <Table.Th>Имя</Table.Th>
                        <Table.Th>Место</Table.Th>
                        <Table.Th>Действия</Table.Th>
                      </Table.Tr>
                    </Table.Thead>
                    <Table.Tbody>
                      {dataPlaces && dataPlaces.length > 0 ? (
                        dataPlaces.map((item) => (
                          <Table.Tr key={item.id}>
                            <Table.Td>{item.user.email}</Table.Td>
                            <Table.Td>{item.user.name}</Table.Td>
                            <Table.Td>{item.place.place}</Table.Td>
                            <Table.Td>
                              <ActionIcon
                                color="red"
                                onClick={() => handleDeleteOrder(
                                  item.id,
                                  item.session.id,
                                  item.coast_set,
                                  item.chatr_id
                                )}
                              >
                                <IconTrash size="1rem" />
                              </ActionIcon>
                            </Table.Td>
                          </Table.Tr>
                        ))
                      ) : (
                        <Table.Tr>
                          <Table.Td colSpan={4} align="center">
                            <Text color="dimmed">Нет данных о пользователях</Text>
                          </Table.Td>
                        </Table.Tr>
                      )}
                    </Table.Tbody>
                  </Table>
                </Paper>
              )}
            </Stack>
          </Container>
        

      <Modal
        opened={orderModal}
        onClose={() => setOrderModal(false)}
        title="Оформление заказа"
        size="md"
      >
        <Stack spacing="md">
          <TextInput
            label="Имя"
            placeholder="Введите ваше имя"
            value={orderForm.name}
            onChange={(e) => setOrderForm({ ...orderForm, name: e.target.value })}
          />
          <TextInput
            label="Email"
            placeholder="Введите ваш email"
            value={orderForm.email}
            onChange={(e) => setOrderForm({ ...orderForm, email: e.target.value })}
          />
          <TextInput
            label="Телефон"
            placeholder="Введите ваш телефон"
            value={orderForm.phone}
            onChange={(e) => setOrderForm({ ...orderForm, phone: e.target.value })}
          />
          <Text size="lg" weight={700}>
            Итого: {totalPrice} ₽
          </Text>
          <Button color="blue" onClick={handleOrderSubmit}>
            Подтвердить заказ
          </Button>
        </Stack>
      </Modal>
    </>
  );
};

export default Film;
