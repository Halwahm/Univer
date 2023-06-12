using System.Collections;
using UnityEngine;

public class MainTankScript : MonoBehaviour
{
    private Camera camera;
    private Coroutine bombSpawnerCoroutine;

    // Start is called before the first frame update
    void Start()
    {
        camera = GetComponent<Camera>();
    }

    // Update is called once per frame
    void Update()
    {
    }

    private IEnumerator BombSpawner()
    {
        const float ScaleIndex = 3;
        float RadiusX = gameObject.GetComponent<Renderer>().bounds.size.x;
        float RadiusZ = gameObject.GetComponent<Renderer>().bounds.size.z;
        var rend = gameObject.transform.position;
        float minX = rend.x - Random.Range(0, RadiusX);
        float minZ = rend.z - Random.Range(0, RadiusZ);
        float maxX = rend.x + Random.Range(0, RadiusX);
        float maxZ = rend.z + Random.Range(0, RadiusZ);
        float ObjectX = Random.Range(minX, maxX);
        float ObjectZ = Random.Range(minZ, maxZ);
        float ObjectY = 40f;
        const float TimeToSpawn = 3f;

        var Object = GameObject.CreatePrimitive(PrimitiveType.Sphere);
        Object.transform.position = new Vector3(ObjectX, ObjectY, ObjectZ);
        Object.GetComponent<Renderer>().material.color = Color.black;
        Object.GetComponent<Renderer>().transform.localScale = new Vector3(ScaleIndex, 1, ScaleIndex);
        Object.AddComponent<Rigidbody>();
        yield return new WaitForSeconds(TimeToSpawn);
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Trigger")
        {
            if (bombSpawnerCoroutine != null)
            {
                StopCoroutine(bombSpawnerCoroutine);
            }
            bombSpawnerCoroutine = StartCoroutine(BombSpawner());
        }
    }
}
