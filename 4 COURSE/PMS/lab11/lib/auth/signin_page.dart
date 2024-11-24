import 'package:flutter/material.dart';

import '../pages/home_page.dart';
import 'auth_service.dart';
import 'signup_page.dart';

class LoginScreen extends StatefulWidget {
  const LoginScreen({Key? key}) : super(key: key);

  @override
  _LoginScreenState createState() => _LoginScreenState();
}

class _LoginScreenState extends State<LoginScreen> {
  final TextEditingController _emailController = TextEditingController();
  final TextEditingController _passwordController = TextEditingController();

  void _showMessage(String message) {
    ScaffoldMessenger.of(context).showSnackBar(
      SnackBar(content: Text(message)),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Login'),
        centerTitle: true,
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            // Email field
            SizedBox(
              width: MediaQuery.of(context).size.width / 2,
              child: TextField(
                key: const Key('loginEmailField'),
                controller: _emailController,
                decoration: const InputDecoration(hintText: 'Email'),
              ),
            ),
            const SizedBox(height: 30.0),
            // Password field
            SizedBox(
              width: MediaQuery.of(context).size.width / 2,
              child: TextField(
                key: const Key('loginPasswordField'),
                controller: _passwordController,
                obscureText: true,
                decoration: const InputDecoration(hintText: 'Password'),
              ),
            ),
            const SizedBox(height: 30.0),
            // Login button
            ElevatedButton(
              key: const Key('loginButton'),
              onPressed: () async {
                final message = await AuthService().login(
                  email: _emailController.text,
                  password: _passwordController.text,
                );
                if (message!.contains('Success')) {
                  Navigator.of(context).pushReplacement(
                    MaterialPageRoute(
                      builder: (context) => const MyHomePage(),
                    ),
                  );
                }
                ScaffoldMessenger.of(context).showSnackBar(
                  SnackBar(content: Text(message)),
                );
              },
              child: const Text('Login'),
            ),
            const SizedBox(height: 30.0),
            // Anonymous login button
            ElevatedButton(
              onPressed: () async {
                final message = await AuthService().signInAnonymously();
                if (message.contains('Success')) {
                  Navigator.of(context).pushReplacement(
                    MaterialPageRoute(
                      builder: (context) => const MyHomePage(),
                    ),
                  );
                } else {
                  ScaffoldMessenger.of(context).showSnackBar(
                    SnackBar(content: Text(message)),
                  );
                }
              },
              child: const Text('Continue as Guest'),
            ),
            const SizedBox(height: 30.0),
            // GitHub Login Button
            ElevatedButton.icon(
              onPressed: () async {
                final message = await AuthService().signInWithGitHub();
                if (message.contains('Success')) {
                  Navigator.of(context).pushReplacement(
                    MaterialPageRoute(
                      builder: (context) => const MyHomePage(),
                    ),
                  );
                } else {
                  _showMessage(message);
                }
              },
              icon: const Icon(Icons.code),
              label: const Text('Sign in with GitHub'),
            ),
            const SizedBox(height: 30.0),
            // Reset password button
            TextButton(
              onPressed: () async {
                if (_emailController.text.isEmpty) {
                  _showMessage('Please enter your email.');
                  return;
                }
                final message = await AuthService().resetPassword(
                  _emailController.text,
                );
                _showMessage(message!);
              },
              child: const Text('Forgot Password? Reset here'),
            ),
            const SizedBox(height: 20),
            // Create Account Button
            TextButton(
              key: const Key('createAccountButton'),
              onPressed: () {
                Navigator.of(context).push(
                  MaterialPageRoute(
                    builder: (context) => const CreateAccount(),
                  ),
                );
              },
              child: const Text('Create Account'),
            ),
          ],
        ),
      ),
    );
  }
}
