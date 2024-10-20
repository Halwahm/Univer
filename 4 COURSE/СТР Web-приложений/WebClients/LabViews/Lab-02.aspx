<%@ Page Title="Lab-02" Language="C#" MasterPageFile="~/Site.Master" Theme="Lab-02" AutoEventWireup="true" CodeBehind="Lab-02.aspx.cs" Inherits="WebClients.LabViews.Lab_02" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <style>
        @import url('https://fonts.googleapis.com/css?family=Roboto:400,700&display=swap');
    </style>

    <div class="main-content">
        <h1 class="page-title"><%: Title %></h1>

        <div class="section get-section">
            <asp:Button runat="server" ID="GETBtn" Text="GET" CssClass="btn get-btn" />
            <asp:TextBox runat="server" ID="GetResult" ReadOnly="true" CssClass="text-output" ToolTip="Result" placeholder="Результат появится здесь"></asp:TextBox>
        </div>

        <div class="section post-section">
            <asp:Button runat="server" ID="POSTBtn" Text="POST" CssClass="btn post-btn" />
            <asp:TextBox runat="server" ID="Result" CssClass="text-input" ToolTip="Parameter 'Result'" placeholder="Введите результат"></asp:TextBox>
            <asp:RegularExpressionValidator runat="server" ControlToValidate="Result" ValidationGroup="validators" Display="Dynamic" ErrorMessage="Некорректный формат числа!" Enabled="true" ForeColor="Red" ValidationExpression="^-?\d+$"></asp:RegularExpressionValidator>
            <asp:Label runat="server" ForeColor="Red" ID="customerr1" CssClass="error-message"></asp:Label>
        </div>

        <div class="section put-section">
            <asp:Button runat="server" ID="PUTBtn" Text="PUT" CssClass="btn put-btn" />
            <asp:TextBox runat="server" ID="Add" CssClass="text-input" ToolTip="Parameter 'Add'" placeholder="Введите значение для добавления"></asp:TextBox>
            <asp:RegularExpressionValidator runat="server" ControlToValidate="Add" ValidationGroup="validators" Display="Dynamic" ErrorMessage="Некорректный формат числа!" Enabled="true" ForeColor="Red" ValidationExpression="^-?\d+$"></asp:RegularExpressionValidator>
            <asp:Label runat="server" ForeColor="Red" ID="customerr2" CssClass="error-message"></asp:Label>
        </div>

        <div class="section delete-section">
            <asp:Button runat="server" ID="DELETEBtn" Text="DELETE" CssClass="btn delete-btn" />
        </div>
    </div>

    <style>
        body {
            font-family: 'Roboto', sans-serif;
            background-color: #1e1e2f;
            color: #ffffff;
            margin: 0;
            padding: 0;
        }

        .main-content {
            max-width: 800px;
            margin: 0 auto;
            padding: 50px 20px;
        }

        .page-title {
            text-align: center;
            margin-bottom: 50px;
            font-size: 2.5em;
            color: #e0e0e0;
        }

        .section {
            background-color: #2e2e3e;
            padding: 40px;
            margin-bottom: 30px;
            border-radius: 15px;
            box-shadow: 0px 10px 20px rgba(0,0,0,0.5);
            position: relative;
        }

        .section::before {
            content: '';
            position: absolute;
            top: -10px;
            left: 50%;
            transform: translateX(-50%);
            width: 60px;
            height: 5px;
            border-radius: 5px;
        }

        .get-section::before {
            background-color: #3498db;
        }

        .post-section::before {
            background-color: #2ecc71;
        }

        .put-section::before {
            background-color: #e67e22;
        }

        .delete-section::before {
            background-color: #e74c3c;
        }

        .btn {
            width: 100%;
            padding: 20px;
            font-size: 1.2em;
            margin-bottom: 25px;
            border: none;
            border-radius: 10px;
            color: #fff;
            cursor: pointer;
            transition: background-color 0.3s ease;
        }

        .get-btn {
            background-color: #2980b9;
        }

        .post-btn {
            background-color: #27ae60;
        }

        .put-btn {
            background-color: #d35400;
        }

        .delete-btn {
            background-color: #c0392b;
        }

        .btn:hover {
            opacity: 0.9;
        }

        .text-input,
        .text-output {
            width: 100%;
            padding: 15px;
            font-size: 1em;
            margin-bottom: 15px;
            border: 1px solid #444;
            border-radius: 5px;
            background-color: #1e1e2f;
            color: #fff;
        }

        .text-input::placeholder,
        .text-output::placeholder {
            color: #888;
        }

        .error-message {
            color: #e74c3c;
            font-size: 0.9em;
        }
    </style>

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>

    <script type="text/javascript">
        $(document).ready(function () {
            $('#<%= GETBtn.ClientID %>').click(function (event) {
                event.preventDefault();
                $.ajax({
                    url: 'http://localhost:82/api/Values/',
                    type: 'GET',
                    success: function (response) {
                        $('#<%= GetResult.ClientID %>').val(response.Result);
                    },
                    error: function (xhr, status, error) {
                        alert('Ошибка: ' + xhr.responseText);
                    }
                });
            });

            $('#<%= POSTBtn.ClientID %>').click(function (event) {
                event.preventDefault();
                var result = $('#<%= Result.ClientID %>').val();
                $.ajax({
                    url: 'http://localhost:82/api/Values/',
                    type: 'POST',
                    contentType: 'application/json',
                    data: JSON.stringify({ Result: parseInt(result) }),
                    success: function (response) {
                        if (response.Status !== "Success") {
                            $('#<%= customerr1.ClientID %>').text(response.Message).show();
                        }
                    },
                    error: function (xhr, status, error) {
                        alert('Ошибка: ' + xhr.responseText);
                    }
                });
            });

            $('#<%= PUTBtn.ClientID %>').click(function (event) {
                event.preventDefault();
                var addValue = $('#<%= Add.ClientID %>').val();
                $.ajax({
                    url: 'http://localhost:82/api/Values/',
                    type: 'PUT',
                    contentType: 'application/json',
                    data: JSON.stringify({ Add: parseInt(addValue) }),
                    success: function (response) {
                        if (response.Status !== "Success") {
                            $('#<%= customerr2.ClientID %>').text(response.Message).show();
                        }
                    },
                    error: function (xhr, status, error) {
                        alert('Ошибка: ' + xhr.responseText);
                    }
                });
            });

            $('#<%= DELETEBtn.ClientID %>').click(function (event) {
                event.preventDefault();
                $.ajax({
                    url: 'http://localhost:82/api/Values/',
                    type: 'DELETE',
                    success: function (response) {
                        if (response.Status === "Success") {
                            $('#<%= customerr2.ClientID %>').text(response.Message).show();
                        }
                    },
                    error: function (xhr, status, error) {
                        alert('Ошибка: ' + xhr.responseText);
                    }
                });
            });
        });
    </script>
</asp:Content>
