using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectGenerator : MonoBehaviour
{
    public GameObject CubePrefab;
    public GameObject SpherePrefab;
    public float SpawnHeight = 5f;

    private Vector3 _minBounds;
    private Vector3 _maxBounds;
    private float _tiltAngle;

    private void Start()
    {
        var component = GetComponent<Renderer>();
        _minBounds = component.bounds.min;
        _maxBounds = component.bounds.max;
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Q))
        {
            SpawnObjectAtRandomPosition(CubePrefab);
        }

        if (Input.GetKeyDown(KeyCode.Space))
        {
            SpawnObjectAtRandomPosition(SpherePrefab);
        }

        if (Input.GetKey(KeyCode.W))
        {
            _tiltAngle += Time.deltaTime * 30f;
            transform.rotation = Quaternion.Euler(0f, 0f, _tiltAngle);
        }
    }

    private void SpawnObjectAtRandomPosition(GameObject prefab)
    {
        var spawnPosition = new Vector3(Random.Range(_minBounds.x, _maxBounds.x), SpawnHeight, Random.Range(_minBounds.z, _maxBounds.z));
        var spawnedObject = Instantiate(prefab, spawnPosition, Quaternion.identity);
        spawnedObject.GetComponent<Rigidbody>().useGravity = true;

        if (prefab == SpherePrefab)
        {
            Destroy(spawnedObject, 5f);
        }
    }
}
