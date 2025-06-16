/* eslint-disable jsx-a11y/alt-text */
/* eslint-disable jsx-a11y/anchor-is-valid */
import "../../../lib/boxicons/css/boxicons.min.css";
import "../../../lib/datatables/datatables.min.css";
import "../../../css/cinemaDataTable.css";
import Store from "../../../store/store";
import React, {useEffect, useState} from "react";
import {Line} from "react-chartjs-2";
import {Card, Container, Grid, Group, Paper, Select, Stack, Text, Title,} from "@mantine/core";
import {IconMovie, IconTicket, IconTrendingUp, IconUsers} from "@tabler/icons-react";
import {notifications} from "@mantine/notifications";
import {
  CategoryScale,
  Chart as ChartJS,
  Legend,
  LinearScale,
  LineElement,
  PointElement,
  Title as ChartTitle,
  Tooltip,
} from "chart.js";

// Регистрация компонентов Chart.js
ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  ChartTitle,
  Tooltip,
  Legend
);

const AdminStatistic = () => {
  const store = new Store();
  const [loading, setLoading] = useState(true);
  const [data, setData] = useState([]);
  const [chartData, setChartData] = useState({
    labels: [],
    datasets: []
  });

  useEffect(() => {
    const fetchData = async () => {
      try {
        const res = await store.GetStatistic();
        setData(res.data);
        processChartData(res.data);
      } catch (error) {
        notifications.show({
          title: 'Ошибка',
          message: 'Не удалось загрузить статистику',
          color: 'red',
        });
      } finally {
        setLoading(false);
      }
    };
    fetchData();
  }, []);

  const processChartData = (data) => {
    // Получаем уникальные даты и сортируем их
    const dates = [...new Set(data.map(item => {
      const date = new Date(item.auditt_date);
      return date.toISOString().split('T')[0];
    }))].sort();

    // Группируем данные по фильмам
    const filmsData = data.reduce((acc, item) => {
      if (!acc[item.auditt_filmname]) {
        acc[item.auditt_filmname] = {};
      }
      const date = new Date(item.auditt_date).toISOString().split('T')[0];
      acc[item.auditt_filmname][date] = parseInt(item.count);
      return acc;
    }, {});

    // Создаем наборы данных для каждого фильма
    const datasets = Object.entries(filmsData).map(([filmName, filmDates], index) => {
      const data = dates.map(date => filmDates[date] || 0);
      return {
        label: filmName,
        data: data,
        borderColor: `hsl(${index * 360 / Object.keys(filmsData).length}, 70%, 50%)`,
        backgroundColor: `hsla(${index * 360 / Object.keys(filmsData).length}, 70%, 50%, 0.1)`,
        tension: 0.4,
        fill: true,
      };
    });

    setChartData({
      labels: dates,
      datasets: datasets
    });
  };

  const chartOptions = {
    responsive: true,
    maintainAspectRatio: false,
    plugins: {
      legend: {
        position: 'top',
        labels: {
          boxWidth: 12,
          padding: 15,
          font: {
            size: 12
          }
        }
      },
      title: {
        display: true,
        text: 'Статистика продаж билетов',
        font: {
          size: 16,
          weight: 'bold'
        }
      },
      tooltip: {
        mode: 'index',
        intersect: false,
      }
    },
    scales: {
      y: {
        beginAtZero: true,
        title: {
          display: true,
          text: 'Количество билетов'
        }
      },
      x: {
        title: {
          display: true,
          text: 'Дата'
        }
      }
    },
    interaction: {
      mode: 'nearest',
      axis: 'x',
      intersect: false
    }
  };

  return (
    <Container size="xl" py="xl">
      <Stack spacing="xl">
        <Paper p="md" radius="md" withBorder>
          <Title order={2} align="center" mb="xl">Статистика продаж</Title>
          <div style={{ height: '500px', position: 'relative' }}>
            <Line data={chartData} options={chartOptions} />
          </div>
        </Paper>
      </Stack>
    </Container>
  );
};

export default AdminStatistic;
