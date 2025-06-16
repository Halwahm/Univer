$(document).ready(function () {
    $('#data-table').DataTable( {
        language: {
            url: '../lib/datatables/dataTables.russian.json'
        },
        info: false,
        search: false,
        lengthMenu: [
            [9, 18, 27, -1],
            [9, 18, 27, 'All'],
        ]
    } );
});
//Авторизация
$('.btn').click(function (e) {
    e.preventDefault();
    let search = $('input[id="search"]').val();
    $.ajax({
        url:'../Add/Search.php',
        type:'POST',
        dataType:'json',
        data:{
            search:search,

        },
        success(data) {
           
            document.getElementById('divfilm').innerHTML =`
                                           <div class="row">
                    <div class="col-xl-12 col-xxl-12 d-flex">
                        <div class="row">
                            <div class="container mt-5">
                                <table id="data-table" class="table table-striped" style="width:100%">
                                    <thead style="display: none">
                                    <tr>
                                        <th></th>
                                    </tr>
                                    </thead>
                                    <tbody id="filmbody" class="row">
                                                     </tbody>
                                    <tfoot>
                                </table>
                            </div>
                        </div>
                    </div>
                </div>
                                        
`;

            if (data.status) {
                data.mas.forEach(function (mas) {


                    document.getElementById('filmbody').innerHTML +=`   
 
                                                <tr class="col-md-4">
                                                    <td>
                                                        <div class="col-md-12">
                                                            <div class="profile-card">

                                                <a href="/Film.php?name=${mas.name}">
                                                    <img src="data:image/jpeg;base64, ${mas.img}"
                                                         class="img img-responsive">
                                                    <div class="profile-name">${mas.name}</div>
                                                    <div class="profile-username">${mas.year}</div>
                                                </a>
                                            </div>
                                        </div>
                                                    </td>
                                                </tr>
                                     `;
                    })
            }
        }
    });
});