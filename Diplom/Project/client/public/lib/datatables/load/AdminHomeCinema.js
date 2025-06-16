$(document).ready(function () {
  $("#data-table").DataTable({
    language: {
      url: "//localhost:3000/lib/datatables/rus/dataTables.russian.json",
    },
    info: false,
    search: false,
    lengthMenu: [
      [9, 18, 27, -1],
      [9, 18, 27, "All"],
    ],
  });
});
