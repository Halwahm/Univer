/* eslint-disable default-case */
/* eslint-disable jsx-a11y/heading-has-content */
/* eslint-disable jsx-a11y/anchor-is-valid */
import React, {useState} from "react";
import {
  Button,
  Card,
  Container,
  Grid,
  Group,
  LoadingOverlay,
  NumberInput,
  Paper,
  Stack,
  Text,
  TextInput,
  Title,
  useMantineTheme
} from "@mantine/core";
import {IconBuilding, IconCurrencyDollar, IconSalt} from "@tabler/icons-react";
import Store from "../../../store/store";
import {useNavigate} from "react-router-dom";
import {notifications} from "@mantine/notifications";

const AdminAddHall = () => {
  const store = new Store();
  const navigate = useNavigate();
  const theme = useMantineTheme();
  const [loading, setLoading] = useState(false);
  const [formData, setFormData] = useState({
    name: "",
    coast_vip: "",
    coast_norm: "",
    count_place: "",
    count_rows: "",
  });

  const handleChange = (field, value) => {
    setFormData(prev => ({ ...prev, [field]: value }));
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    setLoading(true);

    try {
      await store.AddHall(formData);
      
      notifications.show({
        title: 'Успех',
        message: 'Зал успешно добавлен',
        color: 'green',
      });

      // Очищаем форму после успешного добавления
      setFormData({
        name: "",
        coast_vip: "",
        coast_norm: "",
        count_place: "",
        count_rows: "",
      });

      // Перенаправляем на страницу со списком залов
      navigate('/AdminAllHall');
    } catch (error) {
      const errorMessage = Array.isArray(error.response?.data?.message)
        ? error.response.data.message.map(msg => msg.split(':')[1].trim()).join('\n')
        : error.response?.data?.message || 'Произошла ошибка при добавлении зала';

      notifications.show({
        title: 'Ошибка',
        message: errorMessage,
        color: 'red',
      });
    } finally {
      setLoading(false);
    }
  };

  return (
    <Container size="lg" py="xl">
      <Stack spacing="xl">
        <Group position="apart">
          <Title order={2}>Добавить зал</Title>
          <Button
            variant="light"
            leftIcon={<IconBuilding size="1rem" />}
            onClick={() => navigate('/AdminAllHall')}
          >
            К списку залов
          </Button>
        </Group>

        <Card shadow="sm" padding="xl" radius="md" withBorder>
          <LoadingOverlay visible={loading} />
          
          <form onSubmit={handleSubmit}>
            <Stack spacing="xl">
              <Paper p="md" withBorder>
                <Text size="lg" weight={500} mb="md">Основная информация</Text>
                <Grid>
                  <Grid.Col span={4}>
                    <TextInput
                      label="Название зала"
                      placeholder="Введите название"
                      value={formData.name}
                      onChange={(e) => handleChange('name', e.target.value)}
                      icon={<IconBuilding size="1rem" />}
                      required
                    />
                  </Grid.Col>

                  <Grid.Col span={4}>
                    <NumberInput
                      label="Количество рядов"
                      placeholder="Введите количество"
                      value={formData.count_rows}
                      onChange={(value) => handleChange('count_rows', value)}
                      min={1}
                      max={20}
                      required
                    />
                  </Grid.Col>

                  <Grid.Col span={4}>
                    <NumberInput
                      label="Количество мест в ряду"
                      placeholder="Введите количество"
                      value={formData.count_place}
                      onChange={(value) => handleChange('count_place', value)}
                      min={1}
                      max={30}
                      required
                    />
                  </Grid.Col>
                </Grid>
              </Paper>

              <Paper p="md" withBorder>
                <Text size="lg" weight={500} mb="md">Стоимость билетов</Text>
                <Grid>
                  <Grid.Col span={6}>
                    <NumberInput
                      label="Стоимость обычных билетов"
                      placeholder="Введите стоимость"
                      value={formData.coast_norm}
                      onChange={(value) => handleChange('coast_norm', value)}
                      min={0}
                      icon={<IconCurrencyDollar size="1rem" />}
                      required
                    />
                  </Grid.Col>

                  <Grid.Col span={6}>
                    <NumberInput
                      label="Стоимость VIP билетов"
                      placeholder="Введите стоимость"
                      value={formData.coast_vip}
                      onChange={(value) => handleChange('coast_vip', value)}
                      min={0}
                      icon={<IconSalt size="1rem" />}
                      required
                    />
                  </Grid.Col>
                </Grid>
              </Paper>

              <Group position="right" mt="xl">
                <Button
                  variant="default"
                  onClick={() => navigate('/AdminAllHall')}
                >
                  Отмена
                </Button>
                <Button
                  type="submit"
                  loading={loading}
                  leftIcon={<IconBuilding size="1rem" />}
                >
                  Добавить зал
                </Button>
              </Group>
            </Stack>
          </form>
        </Card>
      </Stack>
    </Container>
  );
};

export default AdminAddHall;
