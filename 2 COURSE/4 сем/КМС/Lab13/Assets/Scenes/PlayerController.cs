using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public float MoveSpeed = 5f;
    public float RotateSpeed = 100f;

    void Update()
    {
        var horizontal = Input.GetAxis("Horizontal");
        var vertical = Input.GetAxis("Vertical");
        var mouseX = Input.GetAxis("Mouse X");

        var rotation = mouseX * RotateSpeed * Time.deltaTime;
        transform.Rotate(Vector3.up, rotation);

        var movement = new Vector3(horizontal, 0f, vertical) * MoveSpeed * Time.deltaTime;
        transform.Translate(movement);
    }
}
