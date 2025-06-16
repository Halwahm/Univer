$('.register-but').click(function (e) {
    e.preventDefault();
    $('.msg').text('');
    $('.msg_login').text('');
    $('.msg_email').text('');
    $('.msg_name').text('');
    $('.msg_confirm').text('');
    $('.msg_password').text('');
    $(`input`).removeClass('error');
    let login = $('input[name="login"]').val();
    let password = $('input[name="password"]').val();
    let Confirm_password = $('input[name="Confirm_password"]').val();
    let name = $('input[name="name"]').val();
    let email = $('input[name="email"]').val();

    $.ajax({
        url:'../RegAuth/function.php',
        type:'POST',
        dataType:'json',
        data:{
            login:login,
            password:password,
            Confirm_password:Confirm_password,
            email:email,
            name:name
        },
        success(data) {
            if (data.status) {
                //document.location.href = 'Register.php';
                $('.msg').text(data.message);
            } else {
                switch (data.type){
                    case 1:
                        data.fields.forEach(function (field){
                            $(`input[name="${field}"]`).addClass('error');
                        })
                        $('.msg').text(data.message);
                        break;
                    case 2:
                        $('.msg_login').text(data.message);
                        break;
                    case 3:
                        $('.msg_email').text(data.message);
                        break;
                    case 4:
                        $('.msg_password').text(data.message);
                        break;
                    case 5:
                        $('.msg_confirm').text(data.message);
                        break;
                    case 6:
                        $('.msg_name').text(data.message);
                        break;
                }
            }
        }
    });
});